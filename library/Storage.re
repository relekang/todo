let data = ref(["testy", "tester"]);

let listTodos = () => data^;
let next = () =>
  switch (listTodos() |> List.hd) {
  | item => Some(item)
  | exception (Failure(_)) => None
  };

let add = (item: string) => {
  data := List.append(data^, [item]);
};

let remove = (item: string) => {
  let (_, uncompleted) = List.partition(current => current == item, data^);
  data := uncompleted;
};
