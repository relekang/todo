open Todo;

let run = (profile, item, priority) => {
  Result.unwrap_exn(Storage.add(profile, item, priority))
  Next.run(profile);
};
