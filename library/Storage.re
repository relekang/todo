let getPath = (profile: option(string)) => {
  let config = Config.load();
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

let add = (profile, item, priority) => {
  let data =
    if (priority) {
      [item, ...load(profile)];
    } else {
      List.append(load(profile), [item]);
    };
  save(profile, data);
};

let remove = (profile, item: string) => {
  let (_, uncompleted) =
    List.partition(current => current == item, load(profile));
  save(profile, uncompleted);
};
