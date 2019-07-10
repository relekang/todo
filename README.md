# todo


[![CircleCI](https://circleci.com/gh/yourgithubhandle/todo/tree/master.svg?style=svg)](https://circleci.com/gh/yourgithubhandle/todo/tree/master)


**Contains the following libraries and executables:**

```
todo@0.0.0
│
├─test/
│   name:    TestTodo.exe
│   main:    TestTodo
│   require: todo.lib
│
├─library/
│   library name: todo.lib
│   namespace:    Todo
│   require:
│
└─executable/
    name:    TodoApp.exe
    main:    TodoApp
    require: todo.lib
```

## Developing:

```
npm install -g esy
git clone <this-repo>
esy install
esy build
```

## Running Binary:

After building the project, you can run the main binary that is produced.

```
esy x TodoApp.exe 
```

## Running Tests:

```
# Runs the "test" command in `package.json`.
esy test
```
