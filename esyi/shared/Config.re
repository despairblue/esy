module Path = EsyLib.Path;
module Option = EsyLib.Option;

type t = {
  basePath: Path.t,
  /* TODO: Figure out if we need to keep tarballs, maybe packageCacheDir will
   * suffice - at least yarn does only it. */
  tarballCachePath: Path.t,
  packageCachePath: Path.t,
  esyOpamOverridePath: Path.t,
  opamRepositoryPath: Path.t,
};

let userDirectory = () => {
  let uid = Unix.getuid();
  let home = Unix.getpwuid(uid).Unix.pw_dir;
  /* TODO: fallback to $HOME here */
  /* TODO: make it return result instead. */
  Path.v(home);
};

let make = (~cachePath=?, basePath) => {
  let cachePath =
    Option.orDefault(Path.(userDirectory() / ".esy" / "esyi"), cachePath);

  let tarballCachePath = Path.(cachePath / "archives");
  Files.mkdirp(Path.to_string(tarballCachePath));

  let packageCachePath = Path.(cachePath / "packages");
  Files.mkdirp(Path.to_string(packageCachePath));

  /* XXX: Those two shouldn't be created here as code in ensureGitRepo relies on
   * their existent to perform either glone or update, consider refactoring it.
   */
  let opamRepositoryPath = Path.(cachePath / "opam-repository");
  let esyOpamOverridePath = Path.(cachePath / "esy-opam-override");

  {
    basePath,
    tarballCachePath,
    packageCachePath,
    opamRepositoryPath,
    esyOpamOverridePath,
  };
};
