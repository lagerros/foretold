// Generated by BUCKLESCRIPT VERSION 4.0.5, PLEASE EDIT WITH CARE
'use strict';

var Curry = require("bs-platform/lib/js/curry.js");
var React = require("react");
var ReasonReact = require("reason-react/src/ReasonReact.js");
var Js_primitive = require("bs-platform/lib/js/js_primitive.js");
var Utils$Client = require("../../utils/Utils.bs.js");
var Option$Rationale = require("rationale/src/Option.js");
var Result$Rationale = require("rationale/src/Result.js");
var AgentTable$Client = require("./AgentTable.bs.js");
var AgentTypes$Client = require("./AgentTypes.bs.js");

function botCompetitor(e) {
  if (e !== 497422978) {
    if (e >= 1055622745) {
      return "Objective";
    } else {
      return "Competitive";
    }
  } else {
    return "Aggregation";
  }
}

function agentSection(e) {
  if (e !== undefined) {
    var match = e;
    var match$1 = match[/* user */0];
    var match$2 = match[/* bot */1];
    if (match$2 !== undefined) {
      var r = match$2;
      return React.createElement("div", undefined, React.createElement("h2", undefined, Utils$Client.ste(Option$Rationale.$$default("", r[/* name */3]))), React.createElement("h3", undefined, Utils$Client.ste(Option$Rationale.$$default("", r[/* description */1]))), React.createElement("h3", undefined, Utils$Client.ste(botCompetitor(r[/* competitorType */0]))));
    } else if (match$1 !== undefined) {
      return React.createElement("div", undefined, React.createElement("h2", undefined, Utils$Client.ste(match$1[/* name */1])));
    } else {
      return React.createElement("div", undefined);
    }
  } else {
    return React.createElement("div", undefined);
  }
}

var component = ReasonReact.statelessComponent("User");

function make(id, _) {
  return /* record */[
          /* debugName */component[/* debugName */0],
          /* reactClassInternal */component[/* reactClassInternal */1],
          /* handedOffState */component[/* handedOffState */2],
          /* willReceiveProps */component[/* willReceiveProps */3],
          /* didMount */component[/* didMount */4],
          /* didUpdate */component[/* didUpdate */5],
          /* willUnmount */component[/* willUnmount */6],
          /* willUpdate */component[/* willUpdate */7],
          /* shouldUpdate */component[/* shouldUpdate */8],
          /* render */(function () {
              var query = AgentTypes$Client.GetAgent[/* make */3](id, /* () */0);
              var eta = Curry.app(AgentTypes$Client.GetAgentQuery[/* make */3], [
                    Js_primitive.some(query.variables),
                    undefined,
                    undefined,
                    undefined,
                    undefined,
                    undefined,
                    undefined,
                    undefined,
                    undefined,
                    (function (param) {
                        return Result$Rationale.result(Utils$Client.idd, Utils$Client.idd, Curry._2(Result$Rationale.Infix[/* <$> */1], Utils$Client.apolloResponseToResult(param[/* result */0]), (function (e) {
                                          var match = e.agent;
                                          return React.createElement("div", undefined, agentSection(e.agent), match !== undefined ? ReasonReact.element(undefined, undefined, AgentTable$Client.make(Utils$Client.catOptionals(match[/* measurements */2]), /* array */[])) : React.createElement("div", undefined));
                                        })));
                      })
                  ]);
              return React.createElement("div", undefined, React.createElement("h2", undefined, "Agent Page"), ReasonReact.element(undefined, undefined, eta));
            }),
          /* initialState */component[/* initialState */10],
          /* retainedProps */component[/* retainedProps */11],
          /* reducer */component[/* reducer */12],
          /* jsElementWrapped */component[/* jsElementWrapped */13]
        ];
}

exports.botCompetitor = botCompetitor;
exports.agentSection = agentSection;
exports.component = component;
exports.make = make;
/* component Not a pure module */
