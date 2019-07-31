type result('a) = Pervasives.result('a, exn);

let wrap = fn =>
  switch (fn()) {
  | value => Ok(value)
  | exception error => Error(error)
  };

let unwrap_exn = result =>
  switch (result) {
  | Ok(value) => value
  | Error(error) => raise(error)
  };

let map = (fn: 'a => 'b, result) =>
  switch (result) {
  | Ok(value) => wrap(() => fn(value))
  | Error(_) as error => error
  };

let flatMap = (fn: 'a => result('b), result) =>
  switch (map(fn, result)) {
  | Ok(value) => value
  | Error(_) as error => error
  };

let as_opt = result =>
  switch (result) {
  | Ok(item) => Some(item)
  | Error(error) => None
  };

let catch = (fn, result) =>
  switch (result) {
  | Ok(_) => result
  | Error(error) => wrap(() => fn(error))
  };
