let concatStrings = List.fold_left((a, b) => a ++ b, "");
let concatLines = List.fold_left((a, b) => a ++ "\n" ++ b, "");
