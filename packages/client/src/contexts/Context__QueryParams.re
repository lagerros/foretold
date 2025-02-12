module KeyValuePairs = {
  type t = {
    key: string,
    value: string,
  };

  type ts = array(t);

  let fromSearchParam = (r: string) =>
    r
    |> Js.String.split("&")
    |> E.A.fmap(r => {
         let param = Js.String.split("=", r) |> E.A.to_list;
         switch (param) {
         | [key, value] => Some({key, value})
         | _ => None
         };
       })
    |> E.A.O.concatSome;

  let get = (key, ts: ts) =>
    ts
    |> E.A.filter(r => r.key == key)
    |> E.A.get(_, 0)
    |> E.O.fmap(r => r.value);

  let toUrlParams = (ts: ts) =>
    ts
    |> E.A.fmap(r => r.key ++ "=" ++ r.value)
    |> Js.Array.joinWith("&")
    |> (r => "?" ++ r);

  let make = (key, value) => {key, value};
};

module MeasurableIndex = {
  type state = [ | `OPEN | `JUDGEMENT_PENDING | `JUDGED];

  type query = {state: option(state)};

  let make = (state: option(state)): query => {state: state};

  let stateFromString = (r: string): option(state) =>
    switch (r) {
    | "open" => Some(`OPEN)
    | "closed" => Some(`JUDGED)
    | "pending" => Some(`JUDGEMENT_PENDING)
    | _ => None
    };

  let statetoString = (s: state) =>
    switch (s) {
    | `OPEN => "open"
    | `JUDGED => "closed"
    | `JUDGEMENT_PENDING => "pending"
    };

  let fromString = (r: string): query => {
    let keyValuePairs = KeyValuePairs.fromSearchParam(r);
    let state =
      switch (keyValuePairs |> KeyValuePairs.get("state")) {
      | Some(state) => stateFromString(state)
      | _ => None
      };
    make(state);
  };

  let fromStringWithDefaults = (r: string): query => {
    let q = fromString(r);
    {state: q.state |> E.O.default(`OPEN) |> E.O.some};
  };

  let toKeyValuePairs = (query: query): KeyValuePairs.ts => {
    let state =
      query.state
      |> E.O.fmap(statetoString)
      |> E.O.fmap(r => KeyValuePairs.make("state", r));
    state |> E.O.fmap(e => [|e|]) |> E.O.default([||]);
  };

  let toUrlParams = (r: query): string =>
    r |> toKeyValuePairs |> KeyValuePairs.toUrlParams;
};