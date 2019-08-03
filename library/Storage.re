let get_path = (profile: option(string)) => {
  Config.(
    Config.load()
    |> Result.map(config =>
         switch (profile) {
         | Some(name) => config.basePath ++ "/" ++ name ++ ".json"
         | None => config.basePath ++ "/" ++ config.currentProfile ++ ".json"
         }
       )
  );
};

let load = profile => {
  get_path(profile)
  |> Result.map(path => Yojson.Basic.from_file(path))
  |> Result.map(json => Yojson.Basic.Util.(json |> to_list |> filter_string));
};

let save = (profile, data: list(string)) => {
  get_path(profile)
  |> Result.map(path =>
       Yojson.Basic.(
         to_file(path, `List(List.map(item => `String(item), data)))
       )
     );
};

let all = profile => load(profile);

let next = profile => Result.(all(profile) |> map(List.hd) |> as_opt);

let add = (profile, item, priority) => {
  Result.(
    load(profile)
    |> map(items =>
         if (priority) {
           [item, ...items];
         } else {
           List.append(items, [item]);
         }
       )
    |> flatMap(save(profile))
  );
};

let remove = (profile, item: string) => {
  Result.(
    load(profile)
    |> map(List.partition(current => current == item))
    |> map(snd)
    |> flatMap(save(profile))
  );
};

let delete_profile = profile =>
  get_path(Some(profile)) |> Result.map(Unix.unlink);
