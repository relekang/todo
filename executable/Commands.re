open Todo;
open Cmdliner;

let next = () =>
  (
    switch (Storage.next()) {
    | None =>
      Pastel.(
        <Pastel>
          <Pastel color=Green> "Nothing todo, enjoy your day" </Pastel>
        </Pastel>
      )
    | Some(string) =>
      Pastel.(
        <Pastel>
          <Pastel color=BlackBright> "Up next: " </Pastel>
          <Pastel bold=true> string </Pastel>
        </Pastel>
      )
    }
  )
  |> Console.log;

let listTodos = format => {
  open Pastel;
  let data = Storage.listTodos();
  let next = Storage.next();
  let (_, rest) = List.partition(current => Some(current) == next, data);
  switch (next) {
  | Some(item) =>
    switch (format) {
    | "bitbar" =>
      Bitbar.(
        [
          [Item({title: item, action: None, nestedItems: []}), Line],
          List.map(
            item =>
              Item({
                title: item,
                action: None,
                nestedItems: [
                  {
                    title: "Complete",
                    action: Command(ShellHelpers.complete(item)),
                    nestedItems: [],
                  },
                ],
              }),
            rest,
          ),
          [Refresh],
        ]
        |> List.concat
        |> linesToString
        |> Console.log
      )
    | _ =>
      [
        <Pastel>
          <Pastel bold=true color=Green> " · " </Pastel>
          <Pastel bold=true> item </Pastel>
        </Pastel>,
        ...List.map(
             item =>
               <Pastel>
                 <Pastel bold=true color=Green> " · " </Pastel>
                 item
               </Pastel>,
             rest,
           ),
      ]
      |> Util.concatStrings
      |> Console.log
    }
  | None => ()
  };

  ();
};

let add = item => {
  Storage.add(item);
  next();
  ();
};

let complete = item => {
  Storage.remove(item);
  next();
  ();
};
