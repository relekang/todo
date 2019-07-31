let get_path = (profile: option(string)) => {
  let config = Config.load();
  switch (profile) {
  | Some(name) => config.basePath ++ "/" ++ name ++ ".json"
  | None => config.basePath ++ "/" ++ config.currentProfile ++ ".json"
  };
};

let load = profile => {
  Result.wrap(() => Yojson.Basic.from_file(get_path(profile)))
  |> Result.map(json => Yojson.Basic.Util.(json |> to_list |> filter_string));
};

let save = (profile, data: list(string)) => {
  Result.wrap(() =>
    Yojson.Basic.(
      to_file(
        get_path(profile),
        `List(List.map(item => `String(item), data)),
      )
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
    |> map(Pervasives.snd)
    |> flatMap(save(profile))
  );
};
