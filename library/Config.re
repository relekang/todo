let config_path = Unix.getenv("HOME") ++ "/.todo-config.json";

type t = {
  basePath: string,
  currentProfile: string,
  profiles: list(string),
};

let save = data => {
  Result.wrap(() => {
    Yojson.Basic.Util.(
      Yojson.Basic.to_file(
        config_path,
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
  });
};

let load = () => {
  Result.(
    wrap(() => Yojson.Basic.from_file(config_path))
    |> map(json =>
         Yojson.Basic.Util.{
           basePath: json |> member("basePath") |> to_string,
           currentProfile: json |> member("currentProfile") |> to_string,
           profiles: json |> member("profiles") |> to_list |> filter_string,
         }
       )
    |> catch(error =>
         {
           basePath: Unix.getenv("HOME"),
           currentProfile: "default",
           profiles: ["default"],
         }
       )
    |> flatMap(save)
  );
};
