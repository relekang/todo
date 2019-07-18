open Todo;

let run = (command, name) => {
  Pastel.(
    switch (command) {
    | "add" =>
      let config = Config.load();
      let _ = Config.save({...config, profiles: [name, ...config.profiles]});
      <Pastel color=Green> "Done." </Pastel> |> Console.log;
    | "list" =>
      Config.load().profiles
      |> List.map(profile => profile ++ "\n")
      |> Util.concatStrings
      |> Console.log
    | "activate" =>
      let config = Config.load();
      let _ = Config.save({...config, currentProfile: name});
      <Pastel color=Green> "Done." </Pastel> |> Console.log;
    | "remove" =>
      let config = Config.load();
      let (_, profiles) =
        List.partition(current => current == name, config.profiles);
      let _ = Config.save({...config, profiles});
      <Pastel color=Green> "Done." </Pastel> |> Console.log;
    | _ =>
      <Pastel color=Red> "Unknown profile command." </Pastel> |> Console.log
    }
  );
};
