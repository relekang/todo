open Cmdliner;
let version = "0.2.2";

let default = (Term.(const(_ => Commands.next()) $ const()), Term.info("todo", ~version));

let next = {
  Term.(const(_ => Commands.next()) $ const(), Term.info("next"));
};

let listTodos = {
  Term.(
    const(_ => {
      Commands.listTodos();
      ();
    })
    $ const(),
    Term.info("list"),
  );
};

let add = {
  let item =
    Arg.(value & pos(0, string, "") & info([], ~docv="string", ~doc=""));

  Term.(
    const(item => {
      Commands.add(item);
      ();
    })
    $ item,
    Term.info("add"),
  );
};

let complete = {
  let item =
    Arg.(value & pos(0, string, "") & info([], ~docv="string", ~doc=""));

  Term.(
    const(item => {
      Commands.complete(item);
      ();
    })
    $ item,
    Term.info("complete"),
  );
};

let _ =
  Term.eval_choice(default, [next, listTodos, add, complete]) |> Term.exit;
