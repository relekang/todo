open Todo;

let sorter =
  List.sort((a, b) => {
    Console.log("a: " ++ a);
    Console.log("b: " ++ b);

    Console.log("Which one has higher priority?");
    switch (read_line()) {
    | "a" => (-1)
    | "b" => 1
    | _ => 0
    };
  });

let run = profile => {
  Result.(
    Storage.all(profile)
    |> map(sorter)
    |> flatMap(Storage.save(profile))
    |> map(() => Next.run(profile))
    |> unwrap_exn
  );
};
