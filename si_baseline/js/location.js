/**
 * Created by hpham on 11/3/16.
 */


    // The "calendarLoaded" variable stores information about whether or not the spud has been loaded.
    // It prevents the spud from being reloaded if a visitor returns to the tab multiple times.


// The "select" event handler of the tab control calls the addSpudToTab custom function when the second tab is first selected.
// addSpudToTab in turn calls $Trumba.addSpud, passing in the spudId argument with a value of "divSpud".

// $(function () {
//     $("#tabs").tabs({
//         select: function(event, ui) {
//             if (ui.index == 1 && !calendarLoaded)
//                 addSpudToTab();
//         }
//     });
// });


(function ($) {

    var calendarLoaded = false;

// $Trumba.addSpud is not called inline when the page is first loaded.
// Instead, when a visitor clicks the tab for the first time, addSpudToTab calls the $Trumba.addSpud function.

    function addSpudToTab(venueID) {
        $Trumba.addSpud({
            webName: "smithsonian-events",
            spudType: "main",
            spudId: "divSpud-" + venueID,
            url: { template:"tile", searchinfopanel: "hide", filter3:venueID}

        });
        calendarLoaded = true;
    }
    Drupal.behaviors.siTrumba = {
        attach: function (context, settings) {
            var viewport = ($( window ).width());

            $(".r-tabs-anchor", context).click(function(e) {
                var $this = $(this);
                if($this.attr('href') === '#events' && !calendarLoaded && settings.siTrumba.trumbaID.length) {
                    addSpudToTab(settings.siTrumba.trumbaID);
                }
                if($this.attr('href') === '#collection-highlights' && viewport >= 500) {
                    var $grid = $('.masonry-grid', context).masonry({
                        itemSelector: '.grid-item',
                        columnWidth: '.grid-item',
                        percentPosition: true,
                    });
                    // layout Masonry after each image loads
                    $grid.imagesLoaded().progress( function() {
                        $grid.masonry('layout');
                    });
                }
            });



        }
    };

})(jQuery);