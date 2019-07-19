open StorageBackend;

let getPath = (profile: option(string)) => {
  let config = Config.load();
  switch (profile) {
  | Some(name) => config.basePath ++ "/" ++ name ++ ".json"
  | None => config.basePath ++ "/" ++ config.currentProfile ++ ".json"
  };
};

let backend = {
  load: profile => {
    let channel = open_in(getPath(profile));
    let lines = ref([]);
    try(
      {
        while (true) {
          lines := [input_line(channel), ...lines^];
        };
        lines^ |> Util.concatLines;
      }
    ) {
    | End_of_file =>
      close_in(channel);
      lines^ |> List.rev |> Util.concatLines;
    };
  },

  save: (profile, data) => {
    Yojson.Basic.(to_file(getPath(profile), data));
  },
};
