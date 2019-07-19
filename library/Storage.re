type t = list(string);

let getBackend = profile => {
  open Config;
  let config = load();

  let {storage} =
    config.profiles |> List.find(item => item.name == config.currentProfile);

  switch (storage) {
  | "file" => FileStorage.backend
  | _ => raise(Sys_error("Missing storage backend for " ++ storage))
  };
};

let load: option(string) => t =
  profile => {
    switch (Yojson.Basic.from_string(getBackend().load(profile))) {
    | json => Yojson.Basic.Util.(json |> to_list |> filter_string)
    | exception (Sys_error(_)) => []
    };
  };

let save = (profile, data: t) => {
  Yojson.Basic.Util.(
    getBackend().save(
      profile,
      `List(List.map(item => `String(item), data)),
    )
  );
};

let all = load;

let next = profile =>
  switch (all(profile) |> List.hd) {
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
