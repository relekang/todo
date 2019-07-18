open Todo;

let run = (profile, item) => {
  switch (item) {
  | Some(title) => Storage.remove(profile, title)
  | None =>
    let all = Storage.all(profile);
    all
    |> List.mapi((i, item) => string_of_int(i) ++ ": " ++ item)
    |> Util.concatLines
    |> Console.log;

    Console.log("Which one did you complete?");
    switch (read_int_opt()) {
    | Some(input) =>
      input |> Array.get(Array.of_list(all)) |> Storage.remove(profile)
    | None => Console.log("Oh, so you didn't complete anything?")
    };
  };
  Next.run(profile);
};
