open Todo;

let run = (profile, item) => {
  Storage.remove(profile, item);
  Next.run(profile);
};
