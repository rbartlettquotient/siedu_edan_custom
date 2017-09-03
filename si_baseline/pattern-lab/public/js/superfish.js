/**
 * @file
 * The Superfish Drupal Behavior to apply the Superfish jQuery plugin to lists.
 */

(function ($) {
      // Take a look at each list to apply Superfish to.
        // Process all Superfish lists.
  $(window).load(function () {
    $('#superfish-1').superfish({
        animation: {opacity: 'show', height: 'show'},
        autoArrows: false,
        dropShadows: false,
        speed: "fast"
      }
    );

    $('#superfish-1').sftouchscreen({
      breakpoint: 980,
      breakpointUnit: "px",
      mode: "window_width",
      title: "Main menu"
    });
    $('#superfish-1').sfsmallscreen({
      breakpoint: 980,
      breakpointUnit: "px",
      mode: "window_width",

    });
    $('#superfish-1').supposition();

  });
})(jQuery);