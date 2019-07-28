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

let itemToString: item => string;
let lineToString: bitbarLine => string;
let linesToString: list(bitbarLine) => string;

