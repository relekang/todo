open TestFramework;
open Todo.Bitbar;

describe("Bitbar", ({test}) => {
  test("itemToString() with no action and no nested items", ({expect}) => {
    let result =
      itemToString({title: "the-title", action: None, nestedItems: []});
    expect.string(result).toEqual("the-title | emojize=true\n");
  });

  test("itemToString() with link action and no nested items", ({expect}) => {
    let result =
      itemToString({
        title: "the-title",
        action: Link("http://rolflekang.com"),
        nestedItems: [],
      });
    expect.string(result).toEqual(
      "the-title | href=http://rolflekang.com emojize=true\n",
    );
  });

  test("itemToString() with command action and no nested items", ({expect}) => {
    let result =
      itemToString({
        title: "the-title",
        action: Command(["todo", "complete", "me"]),
        nestedItems: [],
      });
    expect.string(result).toEqual(
      "the-title | terminal=false refresh=true bash=todo param1=complete param2=me emojize=true\n",
    );
  });

  test("itemToString() with no action and nested items", ({expect}) => {
    let result =
      itemToString({
        title: "the-title",
        action: None,
        nestedItems: [{title: "nested-item", action: None, nestedItems: []}],
      });
    expect.string(result).toEqual(
      "the-title | emojize=true\n-- nested-item | emojize=true\n",
    );
  });

  test("lineToString() with Item", ({expect}) => {
    let result =
      lineToString(
        Item({title: "the-title", action: None, nestedItems: []}),
      );
    expect.string(result).toEqual("the-title | emojize=true\n");
  });

  test("lineToString() with Refresh", ({expect}) => {
    let result = lineToString(Refresh);
    expect.string(result).toEqual("Refresh | refresh=true\n");
  });

  test("lineToString() with Line", ({expect}) => {
    let result = lineToString(Line);
    expect.string(result).toEqual("---\n");
  });
});
