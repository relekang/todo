open Todo;
open Cmdliner;

let next = profile =>
  (
    switch (Storage.next(profile)) {
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

let listFormatBitbar = (profile, next, rest) => {
  switch (next) {
  | Some(item) =>
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
    )
  | None =>
    Bitbar.(
      [
        Item({title: ":white_check_mark:", action: None, nestedItems: []}),
        Line,
        Refresh,
      ]
      |> linesToString
    )
  };
};

let listFormatSimple = (profile, next, rest) => {
  switch (next) {
  | Some(item) =>
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
  | None => "Nothing to do"
  };
};

let listTodos = (profile, format) => {
  open Pastel;
  let data = Storage.listTodos(profile);
  let next = Storage.next(profile);
  let (_, rest) = List.partition(current => Some(current) == next, data);

  (
    switch (format) {
    | "bitbar" => listFormatBitbar(profile, next, rest)
    | _ => listFormatSimple(profile, next, rest)
    }
  )
  |> Console.log;
};

let add = (profile, item) => {
  Storage.add(profile, item);
  next(profile);
  ();
};

let complete = (profile, item) => {
  Storage.remove(profile, item);
  next(profile);
  ();
};
