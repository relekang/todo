let nestedPrefix = "-- ";
let argumentsSeparator = "|";

type action =
  | Link(string)
  | Command(list(string))
  | None;

type item = {
  title: string,
  action,
  nestedItems: list(item),
};

type bitbarLine =
  | Item(item)
  | Line
  | Refresh;

let actionToString = action => {
  switch (action) {
  | Link(url) => " href=" ++ url ++ " "
  | Command(command) =>
    let tokens = command |> Array.of_list;
    "terminal=false refresh=true bash="
    ++ tokens[0]
    ++ (
      tokens
      |> Array.mapi((i, item) => (i, item))
      |> Array.fold_left(
           (previous, (i, token)) =>
             i == 0
               ? "" : previous ++ " param" ++ string_of_int(i) ++ "=" ++ token,
           "",
         )
    );
  | None => ""
  };
};

let concat = List.fold_left((a, b) => a ++ b, "");

let rec itemToString = item =>
    item.title
    ++ argumentsSeparator
    ++ actionToString(item.action)
    ++ "\n"
    ++ (item.nestedItems |> List.map(item => nestedPrefix ++ itemToString(item)) |> concat)

let lineToString = bitbarLine => {
  switch (bitbarLine) {
  | Item(item) => itemToString(item)
  | Refresh => "Refresh | refresh=true"
  | Line => "---\n"
  };
};

let linesToString = items => items |> List.map(lineToString) |> concat;
