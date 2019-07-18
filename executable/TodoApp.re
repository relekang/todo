open Cmdliner;
let version = "2.0.0-rc.5";

module CommonOptions = {
  open Arg;

  let profile = {
    let doc = "The profile to use to load the data.";
    value
    & opt(some(string), None)
    & info(
        ["p", "profile"],
        ~docv="<profile>",
        ~env=env_var("PROFILE", ~doc=doc ++ " Same as --profile."),
        ~doc,
      );
  };
};

let default = (
  Term.(const(Next.run) $ CommonOptions.profile),
  Term.info("todo", ~version, ~doc="Manage all the things to do."),
);

let next = {
  Term.(
    const(Next.run) $ CommonOptions.profile,
    info(
      "next",
      ~doc="Show next item on the list. This is also the default command.",
    ),
  );
};

let listTodos = {
  let format =
    Arg.(
      value
      & opt(string, "simple")
      & info(["f", "format"], ~docv="<format>", ~doc="The format to output.")
    );
  Term.(
    const(ListTodos.run) $ CommonOptions.profile $ format,
    info("list", ~doc="List all todos"),
  );
};

let add = {
  let item =
    Arg.(
      required
      & pos(0, some(string), None)
      & info([], ~docv="name", ~doc="The name of the item to add.")
    );
  let priority =
    Arg.(
      value
      & flag
      & info(
          ["P", "priority"],
          ~doc="Should this go to the top of the list.",
        )
    );

  Term.(
    const(Add.run) $ CommonOptions.profile $ item $ priority,
    info("add", ~doc="Add a new item."),
  );
};

let complete = {
  let item =
    Arg.(
      required
      & pos(0, some(string), None)
      & info([], ~docv="name", ~doc="The name of the item to remove.")
    );

  Term.(
    const(Complete.run) $ CommonOptions.profile $ item,
    info("complete", ~doc="Complete an item. This will remove it."),
  );
};

let profiles = {
  let commandArg =
    Arg.(
      required
      & pos(0, some(string), None)
      & info(
          [],
          ~docv="sub-command",
          ~doc=
            "The operation to do with the profile. One of add, remove, list and activate.",
        )
    );
  let nameArg =
    Arg.(
      value
      & pos(1, string, "")
      & info([], ~docv="name", ~doc="The name of the profile")
    );

  Term.(
    const(Profiles.run) $ commandArg $ nameArg,
    info(
      "profiles",
      ~doc=
        "Manage profiles. A profile is a different todo list.
        Different profiles are stored in different files.",
    ),
  );
};

let _ =
  Term.eval_choice(default, [next, listTodos, add, complete, profiles])
  |> Term.exit;
