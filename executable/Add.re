open Todo;

let run = (profile, item, priority) => {
  Storage.add(profile, item, priority);
  Next.run(profile);
};
