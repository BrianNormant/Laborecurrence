import std/strformat
import std/times
type Element = object
  calc: bool
  r: float64

var CACHE: array[100, Element]

when true:
  for i in 0..<CACHE.len: CACHE[i].calc = false
  for i, r in pairs([-1.0, 28, -240, 1948, -16080]):
    CACHE[i].calc = true
    CACHE[i].r = r

const CONST_FACT = [-25.0, -233, -995, -1866, -1080]
proc suite(a: int): float64 =
  if CACHE[a].calc:
    result = CACHE[a].r
  else:
    for i in 0..<5:
      var n: float64
      if CACHE[a-i-1].calc:
        n = CACHE[a-i-1].r
      else:
        n = suite(a-i-1)
      n *= CONST_FACT[i]
      result += n
    CACHE[a].calc = true
    CACHE[a].r = result

when isMainModule:
  let a = 80

  let tic = epochTime()
  let r = suite(a)
  let tac = epochTime()
  let elapsed = (tac - tic) * 1e6
  echo &"a({a}) = {r:.4e}"
  echo &"Took {elapsed} µs"
