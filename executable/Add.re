open Todo;

let run = (profile, item, priority) => {
  Result.unwrap_exn(Storage.add(profile, String.concat(" ", item), priority))
  Next.run(profile);
};
