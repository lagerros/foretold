open Foretold__GraphQL;
open Style.Grid;
open Utils;

module StatusDisplay = Foretold__Component__StatusDisplay;
module Items = Foretold__Components__Measurable__Items;

let component = ReasonReact.statelessComponent("MeasurableFullPresentation");

module Styles = {
  open Css;
  let header =
    style(
      [padding2(~v=`em(1.5), ~h=`em(1.5))]
      @ FC.Base.BaseStyles.fullWidthFloatLeft,
    );
};

let make = (~id: string, ~loggedInUser: Context.Primary.User.t, _children) => {
  ...component,
  render: _self =>
    Queries.MeasurableWithMeasurements.component(~id)
    |> E.F.apply(m =>
         <>
           <Div flexDirection=`row styles=[Styles.header]>
             <Div flex=3>
               <FC.PageCard.H1> {Items.link(~m)} </FC.PageCard.H1>
               <StatusDisplay measurable=m />
               <FC.PageCard.P>
                 {Items.description(~m) |> E.O.React.defaultNull}
               </FC.PageCard.P>
             </Div>
             <Div flex=1>
               {Items.series(~m, ()) |> E.O.React.defaultNull}
               {Items.creatorLink(~m) |> E.O.React.defaultNull}
               {Items.resolutionEndpoint(~m) |> E.O.React.defaultNull}
               {Items.endpointResponse(~m) |> E.O.React.defaultNull}
               {Items.id(~m, ())}
             </Div>
           </Div>
           <>
             {
               let userAgentId =
                 loggedInUser.agent
                 |> E.O.fmap((r: Context.Primary.Agent.t) => r.id);
               let creatorId =
                 m.creator |> E.O.fmap((r: Context.Primary.Agent.t) => r.id);
               userAgentId == creatorId
               || Context.Primary.Measurable.toStatus(m) !== `JUDGED ?
                 <>
                   {"Add a Prediction" |> ste |> E.React.inH2}
                   <Foretold__Components__Measurement__Form
                     measurableId=id
                     isCreator={userAgentId == creatorId}
                   />
                 </> :
                 E.React.null;
             }
             {
               Queries.Measurements.component(
                 ~measurableId=m.id,
                 ~pageLimit=20,
                 ~direction=None,
                 ~innerComponentFn=(
                                     m:
                                       option(
                                         Context.Primary.Connection.t(
                                           Context.Primary.Measurement.t,
                                         ),
                                       ),
                                   ) =>
                 m
                 |> E.O.React.fmapOrNull(
                      (
                        b:
                          Context.Primary.Connection.t(
                            Context.Primary.Measurement.t,
                          ),
                      ) =>
                      b.edges
                      |> E.A.to_list
                      |> Foretold__Components__Measurements__Table.make
                    )
               )
             }
           </>
         </>
       ),
};