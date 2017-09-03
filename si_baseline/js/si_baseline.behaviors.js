(function ($) {
  if (!Drupal.si_baseline) {
    Drupal.si_baseline = {};
  }
  // var imageProcessed = false;
  // var nVer = navigator.appVersion;
  // var nAgt = navigator.userAgent;
  // var browserName  = navigator.appName;
  // var fullVersion  = ''+parseFloat(navigator.appVersion);
  // var majorVersion = parseInt(navigator.appVersion,10);
  // console.log(nVer);
  // console.log(nAgt);
  //alert(nVer +' ' + nAgt + ' ' +browserName + fullVersion);
  luminateExtend.init({
    apiKey: 'BFE9250F55E7096A8D12C01057',
    path: {
      nonsecure: 'http://go.si.edu/',
      secure: 'https://support.si.edu/site/'
    }
  });


  Drupal.behaviors.siBaseline = {
    attach: function (context, settings) {
      var siBaseline = siBaseline || {},
        siteBody = $('body', context),
        site = $('.l-page', context),
        menu = '#page-navigation > div';

      siBaseline = {
        pageInit: function () {
          //set intrinsic height and width of image

          $('a', context).click(function (e) {
            if ($(this).hasClass('prevent-link')) {
              e.preventDefault();
              e.stopPropagation();
            }
          });

          $('.root-facet-list .category', context).each(function () {
            var $this = $(this);
            $this.click(function () {
              $this.toggleClass('expand');
            });
          });
          if ($('.l-header #block-siedu-searches-siedu-searches-block-search-form').length) {
            new UISearch(document.getElementById('block-siedu-searches-siedu-searches-block-search-form'));
          }
          if ($('.page--colorbox .edan-content', context).length) {
            $('.page--colorbox .edan-content a', context).each(function () {
              $(this).attr('target', '_blank');
            });
          }
          if ($('.marquee', context).length) {
            $('.marquee').marquee({
              //speed in milliseconds of the marquee
              duration: 10000,
              //gap in pixels between the tickers
              gap: 32,
              //time in milliseconds before the marquee will start animating
              delayBeforeStart: 0,
              //'left' or 'right'
              direction: 'left',
             // pauseOnHover: true,
              //true or false - should the marquee be duplicated to show an effect of continues flow
              duplicated: true
            });
          }
          if ($('.tooltip-link', context).length) {
            $('.tooltip-link', context).click(function (e) {
              e.preventDefault();
              e.stopPropagation();
            });
          }

         // $('.tooltip-wrapper',context).tooltip('open');
          //this.pageControls();
          this.shareIcons();
          this.newsletter();
          this.sideNav()
        },
        mainController: new ScrollMagic.Controller(),

        pageControls: function ($offset) {

          new ScrollMagic.Scene({
            offset: $offset
          })
            .setClassToggle('body', 'show-page-nav')
            .addTo(this.mainController);

        },
        shareIcons: function () {
          if ($('.share-icon', context).length) {
            $('.share-icon', context).click(function (e) {
              var $this = $(this);
              $this.toggleClass('active');
              e.preventDefault();
              e.stopPropagation();
              $this.siblings('.social-media').toggleClass('active');
            });
          }
        },
        sideNav: function () {
          if ($('.wrapper--superfish .menu-block-wrapper', context).length) {
            // Apply Superfish.
            $('.wrapper--superfish .menu-block-wrapper > ul.menu', context).once('superfish', function () {
              var list = $(this),
                options = Drupal.settings.superfish[1],
                menuParent = $('#superfish-1 > .active-trail', context).clone();
              if (menuParent.hasClass('menuparent')) {
                menuParent.children('ul').remove();
              }
              list.attr('id', 'side-menu').addClass('sf-menu').prepend(menuParent);
              // Check if we are to apply the Supersubs plug-in to it.
              if (options.plugins || false) {
                if (options.plugins.supersubs || false) {
                  list.supersubs(options.plugins.supersubs);
                }
              }

              // Apply Superfish to the list.
              list.superfish({
                autoArrows: false,
                dropShadows: false,
                speed: 100
              });

              // Check if we are to apply any other plug-in to it.
              if (options.plugins || false) {
                if (options.plugins.touchscreen || false) {
                  list.sftouchscreen(options.plugins.touchscreen);
                }
                if (options.plugins.smallscreen || false) {
                  options.plugins.smallscreen.title = 'Section Menu';
                  list.sfsmallscreen(options.plugins.smallscreen);
                }
                if (options.plugins.automaticwidth || false) {
                  list.sfautomaticwidth();
                }
                if (options.plugins.supposition || false) {
                  list.supposition();
                }
                if (options.plugins.bgiframe || false) {
                  list.find('ul').bgIframe({opacity: false});
                }
              }
            });
          }
        },
        newsletter: function () {
          $('#cons_email', context).focus(function () {
            $(this).attr("placeholder", '');
          });
          $('#si-email-signup-form', context).submit(function (event) {
            // cancels the form submission
            event.preventDefault();

            //do very rough check of submitted email address
            var emailString = $('#cons_email', context).val(),
              filter = /^([\w-\.]+)@((\[[0-9]{1,3}\.[0-9]{1,3}\.[0-9]{1,3}\.)|(([\w-]+\.)+))([a-zA-Z]{2,4}|[0-9]{1,3})(\]?)$/;
            if ($('input#denySubmit').val().length != 0) {
              return false;
            }
            else {
              if (filter.test(emailString)) {
                //Now submit the form

                var survey_submit_callback = {
                  error: function (data) {
                    $('#msg-container', context).fadeOut().html(data.errorResponse.message).addClass('error').fadeIn();
                    return false;
                  },
                  success: function (data) {
                    console.log(data);
                    $('.form-details', context).fadeOut();

                    $('#msg-container', context).fadeOut().removeClass('error').html('Thanks for signing up!').fadeIn();
                    $('#signup-footer-container', context).fadeOut();
                  }
                };

                luminateExtend.api.request({
                  api: 'survey',
                  callback: survey_submit_callback,
                  requiresAuth: true,
                  data: 'method=submitSurvey&v=1.0&center_id=1042&survey_id=7760&cons_email=' + emailString + '&cons_email_opt_in=true'
                });

              }
              else {
                $('#msg-container', context).fadeOut().html('Please enter a valid email').addClass('error').fadeIn();
                return false;
              }
            }
          });
        },
        setLayout: function () {
          var $width = $(window).width(),
            $offset = $width > 680 ? 400 : 300;
          if($('body.page--colorbox', context).length) {
            return;
          }
          else {
            this.pageControls($offset);
          }
          // if ($width > 979 && $('.page--theater', context).length) {
          //   $('.page--theater .two-col-bottom .inner', context).matchHeight();
          // }
        },

      };
      siBaseline.pageInit();
      // Generic function that runs on window resize.
      function resizeStuff() {
        siBaseline.setLayout();
      }

      // Runs function once on window resize.
      var TO = false;
      $(window).resize(function () {
        if (TO !== false) {
          clearTimeout(TO);
        }

        // 200 is time in miliseconds.
        TO = setTimeout(resizeStuff, 100);
      }).resize();

    }
  };
})(jQuery);

