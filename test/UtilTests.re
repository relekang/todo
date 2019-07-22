open TestFramework
open Todo.Util

describe("Util", ({test}) => {
  test("concatStrings", ({expect}) => {
    expect.string(concatStrings(["one", "two", "three"])).toEqual("onetwothree")
  })

  test("concatLines", ({expect}) => {
    expect.string(concatLines(["one", "two", "three"])).toEqual("one\ntwo\nthree")
  })
})
