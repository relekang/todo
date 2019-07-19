# todo

## Install

```
npm install -g @relekang/todo@prerelease
```

## Usage

```
NAME
       todo - Manage all the things to do.

SYNOPSIS
       todo COMMAND ...

COMMANDS
       add Add a new item.

       complete
           Complete an item. This will remove it.

       list
           List all todos

       next
           Show next item on the list. This is also the default command.

       pri Prioritise all the tasks.

       profiles
           Manage profiles. A profile is a different todo list. Different
           profiles are stored in different files.

OPTIONS
       --help[=FMT] (default=auto)
           Show this help in format FMT. The value FMT must be one of `auto',
           `pager', `groff' or `plain'. With `auto', the format is `pager` or
           `plain' whenever the TERM env var is `dumb' or undefined.

       -p <profile>, --profile=<profile> (absent PROFILE env)
           The profile to use to load the data.

       --version
           Show version information.

ENVIRONMENT
       These environment variables affect the execution of todo:

       PROFILE
           The profile to use to load the data. Same as --profile.
```

### Bitbar

To use bitbar with todo just create a file like this in your bitbar plugins folder.
Adjust the path variable to include wherever you installed it.

```
#!/bin/bash

PATH=/usr/local/bin

todo list --format bitbar
```


#### Create alias that refreshes bitbar

When using bitbar to show your todos in the menu bar it is nice to have refresh
instantly when running commands. This bash function below will make sure that when
you use `t` instead of `todo` it will also refresh bitbar.


```bash
function t() {
  todo $@
  /usr/bin/open -g bitbar://refreshPlugin?name=*
}
```

## Development

```
npm install -g esy
git clone <this-repo>
esy install
esy build
```

### Running Binary

After building the project, you can run the main binary that is produced.

```
esy x TodoApp.exe
```

### Running Tests

```
# Runs the "test" command in `package.json`.
esy test
```
