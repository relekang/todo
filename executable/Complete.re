open Todo;

let printListWithNumbers = all =>
  all
  |> List.mapi((i, item) => string_of_int(i) ++ ": " ++ item)
  |> Util.concatLines
  |> Console.log;

let ask = (profile, all) => {
  Console.log("Which one did you complete?");
  switch (read_int_opt()) {
  | Some(input) =>
    input |> Array.get(Array.of_list(all)) |> Storage.remove(profile)
  | None => Success(Console.log("Oh, so you didn't complete anything?"))
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
