open FC__Base;
let component = ReasonReact.statelessComponent(__MODULE__);

let link =
  Link.make(
    ~className=
      Css.(
        style([
          marginRight(`em(2.)),
          color(Colors.accentBlue),
          hover([color(Colors.darkAccentBlue)]),
        ])
      ),
  );

let make = children => {
  ...component,
  render: _self =>
    <Div
      styles=[
        Css.(
          style(
            [
              background(Colors.white),
              border(`px(1), `solid, Colors.border),
              borderRadius(`px(5)),
            ]
            @ BaseStyles.fullWidthFloatLeft,
          )
        ),
      ]>
      ...children
    </Div>,
};

let defaultPadding = Css.padding2(~v=`em(0.0), ~h=`em(1.5));

module HeaderRow = {
  let component = ReasonReact.statelessComponent("PageCard HeaderRow");

  module Styles = {
    let itemTopPadding = Css.paddingTop(`em(0.9));
    let itemBottomPadding = Css.paddingBottom(`em(0.9));
  };

  module Title = {
    let component =
      ReasonReact.statelessComponent("PageCard HeaderRow Title");

    let make = children => {
      ...component,
      render: _self =>
        <Div
          styles=[
            Css.(
              style([
                color(Colors.textDark),
                paddingTop(`em(1.2)),
                paddingBottom(`em(1.2)),
                FC__Colors.FontWeights.heavy,
              ])
            ),
          ]>
          ...children
        </Div>,
    };
  };

  let make = children => {
    ...component,
    render: _self =>
      <Div
        styles=[
          Css.(
            style(
              [
                borderBottom(`px(1), `solid, Colors.accentBlueO8),
                defaultPadding,
              ]
              @ BaseStyles.fullWidthFloatLeft,
            )
          ),
        ]>
        ...children
      </Div>,
  };
};

module Body = {
  let component = ReasonReact.statelessComponent("Card Body");
  let make = children => {
    ...component,
    render: _self =>
      <Div styles=[Css.style(BaseStyles.fullWidthFloatLeft)]>
        ...children
      </Div>,
  };
};

module BodyPadding = {
  let component = ReasonReact.statelessComponent("Card BodyPadding");
  let make = children => {
    ...component,
    render: _self =>
      <Div
        styles=[
          Css.style(
            [Css.padding2(~v=`em(1.5), ~h=`em(1.5))]
            @ BaseStyles.fullWidthFloatLeft,
          ),
        ]>
        ...children
      </Div>,
  };
};

module Section = {
  let component = ReasonReact.statelessComponent("Card Section");
  module Styles = {
    open Css;
    let allStyle = style([clear(`both)]);
    let greyStyle = style([backgroundColor(FC__Colors.smokeWhite)]);
    let paddingStyle = style([padding2(~v=`em(1.5), ~h=`em(1.5))]);
    let borderTStyle =
      style([borderTop(`px(1), `solid, FC__Colors.accentBlue1a)]);
    let borderBStyle =
      style([borderBottom(`px(1), `solid, FC__Colors.accentBlue1a)]);
    let flexStyle = style([display(`flex)]);

    let getStyle = (grey, padding, borderTop, borderBottom, flex) =>
      Belt.Array.reduce(
        [|
          (grey, greyStyle),
          (padding, paddingStyle),
          (borderTop, borderTStyle),
          (borderBottom, borderBStyle),
          (flex, flexStyle),
        |],
        allStyle,
        (acc, (flag, style)) =>
        flag ? acc ++ " " ++ style : acc
      );
  };
  let make =
      (
        ~grey=false,
        ~padding=true,
        ~borderTop=false,
        ~borderBottom=false,
        ~flex=false,
        children,
      ) => {
    ...component,
    render: _self =>
      <div
        className={
          Styles.getStyle(grey, padding, borderTop, borderBottom, flex)
        }>
        ...children
      </div>,
  };
};

module VerticalSpace = {
  let component =
    ReasonReact.statelessComponent("Card Vertical Padding Area");
  let spaceStyle = Css.(style([marginTop(`em(1.5))]));
  let make = _children => {
    ...component,
    render: _self => <div className=spaceStyle />,
  };
};

module H1 = {
  let component = ReasonReact.statelessComponent("H1");
  let make = children => {
    ...component,
    render: _self =>
      <h1
        className=Css.(
          style(
            [
              fontSize(`em(1.4)),
              color(`hex("192D44")),
              FC__Colors.FontWeights.heavy,
              marginTop(`em(0.0)),
              marginBottom(`em(0.4)),
            ]
            @ BaseStyles.fullWidthFloatLeft,
          )
        )>
        ...children
      </h1>,
  };
};

module P = {
  let component = ReasonReact.statelessComponent("P");
  let make = children => {
    ...component,
    render: _self =>
      <p
        className=Css.(
          style([
            color(Colors.Text.LightBackground.p),
            lineHeight(`em(1.5)),
          ])
        )>
        ...children
      </p>,
  };
};