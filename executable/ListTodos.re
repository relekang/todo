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
  Pastel.(
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
      |> Util.concatLines
    | None => "Nothing to do"
    }
  );
};

let run = (profile, format) => {
  let next = Storage.next(profile);
  let formatter =
    switch (format) {
    | "bitbar" => listFormatBitbar(profile, next)
    | _ => listFormatSimple(profile, next)
    };

  Result.(
    Storage.all(profile)
    |> map(List.partition(current => Some(current) == next))
    |> map(snd)
    |> map(formatter)
    |> map(Console.log)
    |> unwrap_exn
  );
};
