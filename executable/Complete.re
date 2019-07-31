open Todo;

let printListWithNumbers = all =>
  Pastel.(
    all
    |> List.mapi((i, item) =>
         <Pastel>
           <Pastel color=BlackBright bold=true>
             {string_of_int(i + 1) ++ ": "}
           </Pastel>
           item
         </Pastel>
       )
    |> Util.concatLines
    |> Console.log
  );

let ask = (profile, all) => {
  printListWithNumbers(all);
  Console.log("Which one did you complete?");
  switch (read_int_opt()) {
  | Some(input) =>
    input - 1 |> Array.get(Array.of_list(all)) |> Storage.remove(profile)
  | None => Ok(Console.log("Oh, so you didn't complete anything?"))
  };
};

let run = (profile, item) => {
  (
    switch (item) {
    | Some(title) => Storage.remove(profile, title)
    | None => Storage.all(profile) |> Result.flatMap(ask(profile))
    }
  )
  |> Result.unwrap_exn;
  Next.run(profile);
};
