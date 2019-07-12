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
  let next = Storage.next();
  let (_, rest) = List.partition(current => Some(current) == next, data);
  switch (next) {
  | Some(item) =>
    Console.log(
      Pastel.(
        <Pastel>
          <Pastel bold=true color=Green> " · " </Pastel>
          <Pastel bold=true> item </Pastel>
        </Pastel>
      ),
    )
  | None => ()
  };

  let _ =
    List.map(
      item =>
        Console.log(
          Pastel.(
            <Pastel>
              <Pastel bold=true color=Green> " · " </Pastel>
              item
            </Pastel>
          ),
        ),
      rest,
    );
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
