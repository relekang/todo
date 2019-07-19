type t = {
  load: option(string) => string,
  save: (option(string), Yojson.Basic.t) => unit,
};
