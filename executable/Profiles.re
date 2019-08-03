open Todo;
open Config;

let log_done = _ => Console.log(<Pastel color=Green> "Done." </Pastel>);

let contains_profile = (name, config) => {
  Result.(
    switch (List.find_opt(item => item == name, config.profiles)) {
    | Some(_) => Ok(config)
    | None => Error(Sys_error("Missing profile "))
    }
  );
};

let add = name =>
  Result.(
    Config.load()
    |> map(config =>
         Config.save({...config, profiles: [name, ...config.profiles]})
       )
    |> map(log_done)
  );

let listProfiles = () =>
  Result.(
    Config.load()
    |> map(({profiles}) => List.map(profile => profile ++ "\n", profiles))
    |> map(String.concat("\n"))
    |> map(Console.log)
  );

let activate = name =>
  Result.(
    Config.load()
    |> flatMap(contains_profile(name))
    |> flatMap(config => Config.save({...config, currentProfile: name}))
    |> map(log_done)
  );

let remove = name => {
  Console.log("Are you sure you want to delete the profile?");
  switch (read_line()) {
  | "y"
  | "Y"
  | "yes"
  | "YES" =>
    Result.(
      Config.load()
      |> flatMap(contains_profile(name))
      |> flatMap(config =>
           Config.save({
             ...config,
             profiles:
               config.profiles
               |> List.partition(current => current == name)
               |> snd,
           })
         )
      |> map(log_done)
    )
  | _ => Ok(Console.log("Okay, no worries"))
  };
};

let run = (command, name) => {
  Pastel.(
    (
      switch (command) {
      | "add" => add(name)
      | "list" => listProfiles()
      | "activate" => activate(name)
      | "remove" => remove(name)
      | _ =>
        Console.log(<Pastel color=Red> "Unknown profile command." </Pastel>);
        Ok();
      }
    )
    |> Result.catch(error => {Console.log(error)})
    |> Result.unwrap_exn
  );
};
