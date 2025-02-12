open SLayout;
open Utils;
open Style.Grid;
open Rationale.Function.Infix;

let component = ReasonReact.statelessComponent("Channel Layout Page");

let make =
    (
      agentPage: Context.Routing.AgentPage.t,
      loggedInUser: Context.Primary.User.t,
      {head, body}: LayoutConfig.t,
    ) => {
  ...component,
  render: _ => {
    let agentId = agentPage.agentId;

    let top =
      Foretold__GraphQL.Queries.Agent.component(
        ~id=agentId,
        ({agent}) => {
          let name =
            switch (agent) {
            | {bot: Some(r)} => r.name
            | {user: Some(r)} => r.name
            | _ => ""
            };

          let secondLevel = AgentTabs.Component.tabs(agentPage);

          <>
            <FC.GroupHeader> {name |> ste} </FC.GroupHeader>
            <FC.GroupHeader.SubHeader> secondLevel </FC.GroupHeader.SubHeader>
          </>;
        },
      );

    <Layout__Component__FillWithSidebar channelId=None loggedInUser>
      top
      /* <FC.GroupHeader.SubHeader> secondLevel </FC.GroupHeader.SubHeader> */
      <div className=Styles.container>
        <Div flexDirection=`row styles=[SLayout.Styles.width100]>
          <Div
            styles=[
              Css.(style([marginTop(`em(1.0)), marginRight(`em(2.0))])),
            ]
            flex=3>
            <FC.PageCard>
              <FC.PageCard.HeaderRow> head </FC.PageCard.HeaderRow>
              body
            </FC.PageCard>
          </Div>
        </Div>
      </div>
    </Layout__Component__FillWithSidebar>;
  },
};

let makeWithEl =
    (agentPage: Context.Routing.AgentPage.t, loggedInUser, t: LayoutConfig.t) =>
  make(agentPage, loggedInUser, t) |> E.React.el;