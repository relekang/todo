open Lwt;
open StorageBackend;

let backend = {
  load: profile => {
    open Github;
    print_endline("...........gist");
    let token = Github.Token.of_string("test");
    let id = "test-id";
    let gist = Lwt_main.run(Monad.(run(Gist.get(~token, ~id, ()))));

    Console.log("...");

    print_endline;

    "[]";
  },

  save: (profile, data) => {
    ();
  },
};
