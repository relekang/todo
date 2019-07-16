open Cmdliner;
let version = "0.4.0";

let default = (
  Term.(const(_ => Commands.next(None)) $ const()),
  Term.info("todo", ~version, ~doc="Manage all the things to do."),
);

let next = {
  Term.(
    const(_ => Commands.next(None)) $ const(),
    Term.info(
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
      & info(["f", "format"], ~doc="The format to output.")
    );
  Term.(
    const(format => {
      Commands.listTodos(format);
      ();
    })
    $ format,
    Term.info("list", ~doc="List all todos"),
  );
};

let add = {
  let item =
    Arg.(
      value
      & pos(0, string, "")
      & info([], ~docv="string", ~doc="The name of the item to add.")
    );

  Term.(
    const(item => {
      Commands.add(item);
      ();
    })
    $ item,
    Term.info("add", ~doc="Add a new item."),
  );
};

let complete = {
  let item =
    Arg.(
      value
      & pos(0, string, "")
      & info([], ~docv="string", ~doc="The name of the item to remove.")
    );

  Term.(
    const(item => {
      Commands.complete(item);
      ();
    })
    $ item,
    Term.info("complete", ~doc="Complete an item. This will remove it."),
  );
};

let _ =
  Term.eval_choice(default, [next, listTodos, add, complete]) |> Term.exit;
