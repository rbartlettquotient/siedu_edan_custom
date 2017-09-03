
(function ($) {
    var viewport = $( window ).width();
    Drupal.behaviors.siMedia = {
        attach: function (context, settings) {
            siMedia = {
                init: function () {
                    this.siImages();
                    this.slideshow();
                },
                slideshow: function () {
                    if(settings['siMedia'] && settings['siMedia']['slideshow']) {
                         $.each(settings['siMedia']['slideshow'], function( index, value ) {
                             var swiper = new Swiper('#'+index, {
                                 pagination: '.swiper-pagination',
                                 paginationClickable: true,
                                 slidesPerView:6,
                                 slidesPerColumn: 2,
                                 slidesPerGroup: 6,
                                 spaceBetween: 10,
                                 nextButton: '.swiper-button-next',
                                 prevButton: '.swiper-button-prev',
                                 breakpoints: {
                                     // when window width is <= 400px
                                     400: {
                                         slidesPerView:2,
                                         slidesPerGroup: 2,
                                         slidesPerColumn:1,
                                         spaceBetween: 5
                                     },
                                     // when window width is <= 669px
                                     979: {
                                         slidesPerView:3,
                                         slidesPerColumn: 2,
                                         slidesPerGroup: 3,
                                     },
                                     // when window width is <= 1279px
                                     1279: {
                                         slidesPerView: 4,
                                         slidesPerColumn: 2,
                                         slidesPerGroup: 4,
                                     }
                                 }

                             });
                             $('#' + index).parent('.swiper-container-wrapper').addClass('has-nav');
                         });

                        // var swiper = new Swiper('.swiper-container', {
                        //     pagination: '.swiper-pagination',
                        //     slidesPerView: 3,
                        //     slidesPerColumn: 2,
                        //     paginationClickable: true,
                        //     spaceBetween: 30
                        // });
                    }
                },
                constructMedia: function (mediaID, params, container, context) {
                    var mediaHTML = '',
                        $this = $('#' + mediaID),
                        mediaHeight = params.type === 'pdf' ? 720 : container.width() * (9/16);
                    console.log(viewport);
                    container.children().removeClass('active');
                    if(params.caption.length){
                        mediaHTML += '<div>' + params.caption + '</div>';
                    }
                    if(params.type === 'video' || params.type === 'audio') {
                        var video = $('#mediaplayer-' + mediaID +'_wrapper');
                        //video.height(mediaHeight);
                        $('.mediaplayer-wrapper', container).removeClass('active');
                        video.parent().addClass('active');
                    }
                    else {
                        $('.media-container', container).removeClass('active');
                        if($this.hasClass('image')) {
                            mediaHTML += '<img src="' + params.src.default +'" alt="' + params.info + '" />';
                        }

                        else {
                            if (viewport < 620) {
                                mediaHTML += '<img src="' + params.src.mobile +'" alt="' + params.info + '" />';
                            }
                            else {
                                mediaHTML += '<iframe title="' + params.info + '" src="' + params.src.default +'" width="100%" height="'+ mediaHeight +'" frameborder="0" scroll="no"></iframe>';
                                mediaHTML += '<a href="' + params.src.fullscreen +'" class="btn btn-alt fullsize" target="_blank">'+
                                             '<span class="sr-only">View fullsize image of ' + params.info + '</span></a>';
                            }
                        }

                        $('.media-container', container).addClass('active media-images').html(mediaHTML);
                    }

                },
                siImages: function () {
                    if($('.media-container', context).length) {
                        $('.media-container', context).hover(function() {
                            $(this).addClass('hover');
                            },
                            function () {
                                $(this).removeClass('hover');
                            });
                    }
                    if($('.mediaplayer-wrapper', context).length) {
                        $('.mediaplayer-wrapper', context).each(function () {
                            var mediaHeight = $(this).width() * (9/16);
                           $(this).children('div').height(mediaHeight);
                        });
                    }
                    if(settings['siMedia'] && settings['siMedia']['images']) {
                        if($('.thumbnail-wrapper', context).length) {
                            var mcAnchors = $('.thumbnail-wrapper a', context),
                              initMedia = $('.thumbnail-wrapper li', context).first().children('a'),
                              initID = initMedia.attr('id'),
                              container = initMedia.parents('.record-media');

                            initMedia.removeClass('active').addClass('active');
                            if (settings['siMedia']['images'][initID]) {
                                this.constructMedia(initID, settings['siMedia']['images'][initID], container);
                            }
                            mcAnchors.click(function(ev) {
                                ev.preventDefault();
                                var $this = $(this, context),
                                  mediaID = $this.attr('id');
                                if (settings['siMedia']['images'][mediaID]) {
                                    mcAnchors.removeClass('active');
                                    $this.addClass('active');
                                    siMedia.constructMedia(mediaID, settings['siMedia']['images'][mediaID], container);
                                }

                            });
                        }
                        else {
                            if (viewport > 979) {
                                $.each(settings['siMedia']['images'], function (index, params) {
                                    var container = $('#' + index).parents('.record-media'),
                                      mediaHeight = container.width() * (9/16)
                                      mediaHTML = '<iframe title="' + params.info + '" src="' + params.src.default + '" width="100%" height="' + mediaHeight + '" frameborder="0" scroll="no"></iframe>';
                                    mediaHTML += '<a href="' + params.src.fullscreen +'" class="btn btn-alt fullsize" target="_blank">'+
                                        '<span class="sr-only">View fullsize image of ' + params.info + '</span></a>';

                                    $('.media-container', container).html(mediaHTML);

                                });
                            }
                        }
                    }
                }
            }
            siMedia.init();
            // if(settings['siMedia']['slideshow']) {
            //
            // }
            //
            function resizeStuff() {
                siMedia.slideshow();
                siMedia.siImages();
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