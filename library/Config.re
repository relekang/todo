let configPath = Unix.getenv("HOME") ++ "/.todo-config.json";

type profile = {
  name: string,
  storage: string,
};

type t = {
  basePath: string,
  currentProfile: string,
  profiles: list(profile),
};

let save = data => {
  Yojson.Basic.Util.(
    Yojson.Basic.to_file(
      configPath,
      `Assoc([
        ("basePath", `String(data.basePath)),
        ("currentProfile", `String(data.currentProfile)),
        (
          "profiles",
          `List(
            List.map(
              item =>
                `Assoc([
                  ("name", `String(item.name)),
                  ("storage", `String(item.storage)),
                ]),
              data.profiles,
            ),
          ),
        ),
      ]),
    )
  );
  data;
};
let load = () => {
  Yojson.Basic.Util.(
    switch (Yojson.Basic.from_file(configPath)) {
    | json => {
        basePath: json |> member("basePath") |> to_string,
        currentProfile: json |> member("currentProfile") |> to_string,
        profiles:
          json
          |> member("profiles")
          |> to_list
          |> List.map(item =>
               {
                 name: item |> member("name") |> to_string,
                 storage: item |> member("storage") |> to_string,
               }
             ),
      }
    | exception (Sys_error(_)) =>
      {
        basePath: Unix.getenv("HOME"),
        currentProfile: "default",
        profiles: [{name: "default", storage: "file"}],
      }
      |> save
    }
  );
};
