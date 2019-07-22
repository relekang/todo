let concatStrings = List.fold_left((a, b) => a ++ b, "");
let concatLines = list => list |>List.fold_left((a, b) => a ++ "\n" ++ b, "") |> String.trim;
