open Todo;
open Cmdliner;

let next = () =>
  (
    switch (Storage.next()) {
    | None =>
      Pastel.(
        <Pastel>
          <Pastel color=Green> "Nothing todo, enjoy your day" </Pastel>
        </Pastel>
      )
    | Some(string) =>
      Pastel.(
        <Pastel>
          <Pastel color=BlackBright> "Up next: " </Pastel>
          <Pastel bold=true> string </Pastel>
        </Pastel>
      )
    }
  )
  |> Console.log;

let listTodos = () => {
  open Pastel;
  let data = Storage.listTodos();
  let _ = List.map(Console.log, data);
  ();
};

let add = item => {
  Storage.add(item);
  next();
  ();
};

let complete = item => {
  Storage.remove(item);
  next();
  ();
};
