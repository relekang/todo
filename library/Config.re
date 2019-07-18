let configPath = Unix.getenv("HOME") ++ "/.todo-config.json";

type t = {
  basePath: string,
  currentProfile: string,
  profiles: list(string),
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
          `List(List.map(item => `String(item), data.profiles)),
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
        profiles: json |> member("profiles") |> to_list |> filter_string,
      }
    | exception (Sys_error(_)) =>
      {
        basePath: Unix.getenv("HOME"),
        currentProfile: "default",
        profiles: ["default"],
      }
      |> save
    }
  );
};
