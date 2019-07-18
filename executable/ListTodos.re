open Todo;

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

let run = (profile, format) => {
  open Pastel;
  let data = Storage.all(profile);
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
