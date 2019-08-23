/*
 * NotificationsView.re
 *
 * View for KeyDisplayer
 */

open Revery;
open Revery.UI;
open Revery.UI.Components;

module Core = Oni_Core;
open Oni_Model;

let bgc = Color.rgb(0.1, 0.1, 0.1);
let fgc = Color.rgb(0.9, 0.9, 0.9);

let notificationWidth = Core.Constants.default.notificationWidth;

let notification =
    (
      ~children as _,
      ~onClose,
      ~background,
      ~foreground,
      ~icon,
      ~uiFont,
      ~message,
      ~title: string,
      (),
    ) => {
  <AllowPointer>
    <Padding padding=16>
      <BoxShadow
        boxShadow={Style.BoxShadow.make(
          ~xOffset=-15.,
          ~yOffset=5.,
          ~blurRadius=30.,
          ~spreadRadius=5.,
          ~color=Color.rgba(0., 0., 0., 0.2),
          (),
        )}>
        <View
          style=Style.[
            width(notificationWidth),
            backgroundColor(background),
          ]>
          <View
            style=Style.[
              flexDirection(`Row),
              justifyContent(`Center),
              alignItems(`Center),
            ]>
            <View
              style=Style.[
                flexGrow(0),
                justifyContent(`Center),
                alignItems(`Center),
              ]>
              <Container width=40 height=40>
                <Center>
                  <FontIcon
                    fontFamily={Core.Constants.default.fontAwesomeSolidPath}
                    icon
                    fontSize=16
                    backgroundColor=background
                    color=foreground
                  />
                </Center>
              </Container>
            </View>
            <View
              style=Style.[
                flexGrow(1),
                flexDirection(`Column),
                maxWidth(notificationWidth - 80),
              ]>
              <Padding padding=8>
                <Text
                  style=Style.[
                    fontFamily(uiFont),
                    fontSize(16),
                    textWrap(TextWrapping.NoWrap),
                    backgroundColor(background),
                    color(foreground),
                    marginRight(16),
                    flexGrow(0),
                  ]
                  text=title
                />
                <Text
                  style=Style.[
                    fontFamily(uiFont),
                    fontSize(14),
                    backgroundColor(background),
                    color(foreground),
                    marginRight(16),
                    marginVertical(8),
                    flexGrow(0),
                  ]
                  text=message
                />
              </Padding>
            </View>
            <View
              style=Style.[
                flexGrow(0),
                justifyContent(`Center),
                alignItems(`Center),
              ]>
              <Clickable onClick={_ => onClose()}>
                <Container width=40 height=40>
                  <Center>
                    <Text
                      style=Style.[
                        fontFamily(uiFont),
                        fontSize(16),
                        textWrap(TextWrapping.NoWrap),
                        backgroundColor(background),
                        color(foreground),
                        flexGrow(0),
                      ]
                      text="x"
                    />
                  </Center>
                </Container>
              </Clickable>
            </View>
          </View>
        </View>
      </BoxShadow>
    </Padding>
  </AllowPointer>;
};

let createElement = (~children as _, ~state: State.t, ()) => {
  let uiFont = state.uiFont.fontFile;

  let {
    notificationInfoBackground,
    notificationInfoForeground,
    notificationSuccessBackground,
    notificationSuccessForeground,
    notificationWarningBackground,
    notificationWarningForeground,
    notificationErrorBackground,
    notificationErrorForeground,
    _,
  }: Core.Theme.t =
    state.theme;

  let notifications =
    state.notifications
    |> List.map((n: Notification.t) => {
         let (icon, background, foreground) =
           switch (n.notificationType) {
           | Actions.Success => (
               FontAwesome.checkCircle,
               notificationSuccessBackground,
               notificationSuccessForeground,
             )
           | Actions.Warning => (
               FontAwesome.exclamationTriangle,
               notificationWarningBackground,
               notificationWarningForeground,
             )
           | Actions.Error => (
               FontAwesome.exclamationCircle,
               notificationErrorBackground,
               notificationErrorForeground,
             )
           | _ => (
               FontAwesome.infoCircle,
               notificationInfoBackground,
               notificationInfoForeground,
             )
           };

         let onClose = () => GlobalContext.current().hideNotification(n.id);

         <notification
           background
           foreground
           onClose
           uiFont
           icon
           title={n.title}
           message={n.message}
         />;
       });

  <Positioned bottom=50 right=50> ...notifications </Positioned>;
};