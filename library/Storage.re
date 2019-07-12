let path = Unix.getenv("HOME") ++ "/.todo-data.json";

let load = () => {
  let json = Yojson.Basic.from_file(path);
  Yojson.Basic.Util.(json |> to_list |> filter_string);
};

let save = (data: list(string)) => {
  Yojson.Basic.(
    to_file(path, `List(List.map(item => `String(item), data)))
  );
};

let listTodos = () => {
  load();
};

let next = () =>
  switch (listTodos() |> List.hd) {
  | item => Some(item)
  | exception (Failure(_)) => None
  };

let add = (item: string) => {
  let data = List.append(load(), [item]);
  save(data);
};

let remove = (item: string) => {
  let (_, uncompleted) = List.partition(current => current == item, load());
  save(uncompleted);
};
