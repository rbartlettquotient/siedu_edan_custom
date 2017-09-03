(function ($) {
    Drupal.behaviors.siSlideshow = {
        attach: function (context, settings) {
            siSlides = {
                init: function () {
                    this.slideshow();

                    $('.si-filters a', context).click(function (e) {
                        e.preventDefault();
                        e.stopPropagation();

                        var parent = $(this).attr('data-parent'),
                            url = $(this).attr('data-url'),
                            optionset = settings['siSlides']['owl'][parent],
                            container = $('#' + parent + ' .owl-carousel', context);
                        $('#' + parent + ' .si-filters a', context).removeClass('active');
                        $(this).addClass('active');

                        container.html('').append('<div class="ajax-progress-throbber"><div class="loading"></div></div>');
                        $.ajax({
                            // type:"POST",
                            url: url,
                            success: function (data) {
                                var $newElements = $('.view-theaters > .view-content > .views-row', data),
                                    $items = $newElements.length;
                                container.owlCarousel('destroy');
                                console.log($newElements.length);

                                container.html($newElements);
                                if ($items > 2) {
                                    container.owlCarousel(optionset);
                                }
                                else {
                                    container.owlCarousel({
                                        items: 1,
                                        loop: false,
                                        margin: 10,
                                        dots: 0,
                                        slideBy: 1,
                                        nav: true,
                                        video: true,
                                        lazyLoad: true,
                                        autoWidth: true,
                                        responsive: {
                                            620: {
                                                items: $items,
                                                slideBy: $items,
                                                stagePadding: 20

                                            }
                                        }
                                    });

                                }

                                $('.owl-prev', '#' + parent + ' .owl-carousel').html('<span>Previous</span>')
                                $('.owl-next', '#' + parent + ' .owl-carousel').html('<span>Next</span>')


                            }
                        });
                    });
                },
                slideshow: function () {
                    var viewport = ($(window).width()),
                        numPer = viewport < 979 ? (viewport > 669 ? 3 : 1) : (viewport > 1280 ? 6 : 4);
                    //console.log(viewport);
                    if (settings['siSlides']) {
                        $.each(settings['siSlides'], function (index, value) {
                            // console.log(index);
                            if (index === 'owl') {
                                $.each(value, function (slideID, optionset) {
                                    //console.log(optionset);
                                    $('#' + slideID + ' .owl-carousel').owlCarousel(optionset);
                                    $('.owl-prev', '#' + slideID + ' .owl-carousel').html('<span>Previous</span>')
                                    $('.owl-next', '#' + slideID + ' .owl-carousel').html('<span>Next</span>')

                                });

                            }
                            else {
                                $.each(value, function (slideID, optionset) {

                                    var swiper = new Swiper('#' + slideID, {
                                        slidesPerView: 6,
                                        slidesPerGroup: 6,
                                        loop: true,
                                        nextButton: '.swiper-button-next',
                                        prevButton: '.swiper-button-prev',
                                        // Responsive breakpoints
                                        breakpoints: {
                                            // when window width is <= 400px
                                            400: {
                                                slidesPerView: 1,
                                                slidesPerGroup: 1
                                            },
                                            // when window width is <= 480px
                                            669: {
                                                slidesPerView: 2,
                                                slidesPerGroup: 2
                                            },
                                            // when window width is <= 640px
                                            979: {
                                                slidesPerView: 3,
                                                slidesPerGroup: 3
                                            },
                                            1279: {
                                                slidesPerView: 6,
                                                slidesPerGroup: 6
                                            }

                                        }
                                    });

                                });

                            }
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
            }
            siSlides.init();
            // if(settings['siSlides']['slideshow']) {
            //
            // }
            //
            function resizeStuff() {
                siSlides.slideshow();
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