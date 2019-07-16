let configPath = Unix.getenv("HOME") ++ "/.todo-config.json";

type config = {
  basePath: string,
  currentProfile: string,
  profiles: list(string),
};

let loadConfig = () => {
  Yojson.Basic.Util.(
    switch (Yojson.Basic.from_file(configPath)) {
    | json => {
        basePath: json |> member("basePath") |> to_string,
        currentProfile: json |> member("currentProfile") |> to_string,
        profiles: json |> member("profiles") |> to_list |> filter_string,
      }
    | exception (Sys_error(_)) => {
        basePath: Unix.getenv("HOME"),
        currentProfile: "default",
        profiles: ["default"],
      }
    }
  );
};

let getPath = profile => {
  let config = loadConfig();
  switch (profile) {
  | Some(name) => config.basePath ++ "/" ++ name ++ ".json"
  | None => config.basePath ++ "/" ++ config.currentProfile ++ ".json"
  };
};

let load = profile => {
  switch (Yojson.Basic.from_file(getPath(profile))) {
  | json => Yojson.Basic.Util.(json |> to_list |> filter_string)
  | exception (Sys_error(_)) => []
  };
};

let save = (profile, data: list(string)) => {
  Yojson.Basic.(
    to_file(
      getPath(profile),
      `List(List.map(item => `String(item), data)),
    )
  );
};

let listTodos = profile => {
  load(profile);
};

let next = profile =>
  switch (listTodos(profile) |> List.hd) {
  | item => Some(item)
  | exception (Failure(_)) => None
  };

let add = (profile, item: string) => {
  let data = List.append(load(profile), [item]);
  save(profile, data);
};

let remove = (profile, item: string) => {
  let (_, uncompleted) =
    List.partition(current => current == item, load(profile));
  save(profile, uncompleted);
};
