/**
 * Created by phamh on 7/26/16.
 */
(function ($) {
  // Take a look at each list to apply Superfish to.
  // Process all Superfish lists.
  $(window).load(function () {
    new UISearch( document.getElementById( 'search-block-form' ) );
  });
})(jQuery);