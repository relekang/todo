type result('a) =
  | Success('a)
  | Failure(exn);

let wrap = fn =>
  switch (fn()) {
  | value => Success(value)
  | exception error => Failure(error)
  };

let unwrap_exn = result =>
  switch (result) {
  | Success(value) => value
  | Failure(error) => raise(error)
  };

let map = (fn: 'a => 'b, result) =>
  switch (result) {
  | Success(value) => wrap(() => fn(value))
  | Failure(error) => Failure(error)
  };

let flatMap = (fn: 'a => result('b), result) =>
  switch (map(fn, result)) {
  | Success(value) => value
  | Failure(_) as failure => failure
  };

let as_opt = result =>
  switch (result) {
  | Success(item) => Some(item)
  | Failure(error) => None
  };
