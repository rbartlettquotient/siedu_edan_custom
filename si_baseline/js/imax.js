(function ($) {


  //holder calendar date
  function dateHolder(eventDates) {
    this.before = function (date) {
      date = date.getFullYear() + '-' + (date.getMonth() + 1) + '-' + date.getDate();
      // console.log(date);
      if ($.inArray(date, eventDates) > -1) return [true, 'with_events']; else return [false, 'without_events'];
      // if ($.inArray(date, eventDates) > -1) return [true, 'with_events']; else return [false, 'without_events'];{
      //   // if (date == activeDate) {
      //   //   return [true, 'active with_events'];
      //   // }
      //   // else {
      //     return [true, 'with_events'];
      //   // }
      //   //
      // } else {
      //   return [false, 'without_events'];
      // }
    }
  }


  Drupal.behaviors.siImax = {
    attach: function (context, settings) {
        if (settings['siDatepicker']) {
          $.each(settings['siDatepicker'], function (index, value) {
            $('#' + index, context).once('siDatepicker', function () {
              var start_date = value['filterDate'];
               // default_date =  new Date(start_date),
               // dateFormat = value['picker_type'] == 'default' ? 'mm/dd/yy' : 'yy-mm-dd';
              //dateFormat = 'yy-mm-dd';

              if (!$('#' + index + ' #datepicker', context).get(0)) return;
              var container = $('#' + index + ' #datepicker', context);
              container.siblings('form').hide();
              //if(value['picker_type'] == 'default') container.siblings('form').hide();
              container.datepicker({
                dateFormat: "yy-mm-dd",
                defaultDate: start_date,
                beforeShowDay: function (date) {
                  return false;
                }
              });
              var url = container.attr('data-url');
              if (typeof url != 'undefined') {
                $.getJSON(url, function (data) {
                  var eventDates = [];
                  $.each(data.dates, function (key, date) {
                    $.each(date, function (key, field) {
                      //eventDates['+ field +'] = 1;
                      if ($.inArray(field, eventDates) == -1) {
                        eventDates.push(field);
                      }
                    });
                  });
                  //activeDate = default_date.getFullYear() + '-' + (default_date.getMonth() + 1) + '-' + default_date.getDate();
                  var holder = new dateHolder(eventDates);

                  container.datepicker("destroy");
                  container.datepicker({
                    dateFormat: "yy-mm-dd",
                    defaultDate: start_date,
                    beforeShowDay: function (date) {
                      return holder.before(date);
                    },
                    onSelect: function (date) {
                      // if (curr_date == date) date = '';
                      $(this).addClass('active');
                      Drupal.settings.siDatepicker[index]['date'] = date;
                      container.append('<div id="placeholder"><div class="loading"></div></div>');
                      if(value['picker_type'] === 'default') {
                        $('#edit-field-date-value-value-date', context).trigger('change');
                      }
                      else {
                        $('#edit-field-start-date-value-value-date', context).trigger('change');
                      }

                    }
                  });//end datepicker
                  if(value['picker_type'] === 'default') {
                    $("#datepicker", context).datepicker('option', 'altField', '#edit-field-date-value-value-date');
                  }
                  else {
                    $("#datepicker", context).datepicker('option', 'altField', '#edit-field-start-date-value-value-date');
                  }
                });
              }

            });
          });
        }

        // if ($('#edit-field-date-value-value-date', context).length > 0) {
        //   var start_date = $('#edit-field-date-value-value-date', context).length > 0 ? $('#edit-field-date-value-value-date', context).val() : '';
        // }
        // else {
        //   var start_date = '';
        // }
        // $('#datepicker', context).siblings('form').hide();
        // var default_date = start_date === '' ? new Date() : new Date(start_date);
        // // curr_date = start_date;
        // $("#datepicker", context).datepicker({
        //   dateFormat: "mm/dd/yy",
        //   defaultDate: start_date,
        //   beforeShowDay: function (date) {
        //     return false;
        //   }
        // });
        // if (start_date == ''){
        //   $( "#datepicker",context).find('.ui-state-active').removeClass('ui-state-active');
        // }

        // var url = $('#datepicker', context).attr('data-url');
        // if (typeof url != 'undefined') {
        //
        //   $.getJSON(url, function (data) {
        //     var eventDates = [];
        //     $.each(data.dates, function (key, date) {
        //
        //       $.each(date, function (key, field) {
        //         //eventDates['+ field +'] = 1;
        //         if ($.inArray(field, eventDates) == -1) {
        //           eventDates.push(field);
        //         }
        //
        //       });
        //
        //     });
        //     activeDate = default_date.getFullYear() + '-' + (default_date.getMonth() + 1) + '-' + default_date.getDate();
        //     // activeDate = start_date.length === 0 ? default_date.getFullYear() + '-' + (default_date.getMonth() + 1) + '-' + default_date.getDate() :  default_date.getFullYear() + '-' + (default_date.getMonth() + 1) + '-' + (default_date.getDate() +1);
        //
        //     var holder = new Drupal.si_baseline.dateHolder(eventDates);
        //
        //     $("#datepicker", context).datepicker("destroy");
        //     $("#datepicker", context).datepicker({
        //       dateFormat: "mm/dd/yy",
        //       defaultDate: default_date,
        //       //altFormat: "mm/dd/yy",
        //       altField: '#edit-field-date-value-value-date',
        //       beforeShowDay: function (date) {
        //         return holder.before(date, activeDate);
        //       },
        //
        //       onSelect: function (date) {
        //         // if (curr_date == date) date = '';
        //         $(this).addClass('ui-state-custom');
        //         // $('#edit-field-date-value-value-date',context).val(date);
        //         $('#edit-field-date-value-value-date', context).trigger('change');
        //         $("#datepicker", context).append('<div class="ajax-progress-throbber"><div class="loading"></div></div>');
        //         // $.ajax({
        //         //   // type:"POST",
        //         //   url: url,
        //         //   success: function (data) {
        //         //     var $newElements = $(item, data),
        //         //       newUrl = Drupal.siSearch.queryURL(url);
        //         //     newSelector.attr('href', newUrl);
        //         //
        //         //     $('.loading').remove();
        //         //     // console.log($newElements);
        //         //     Container.append($newElements);
        //         //     $newElements.imagesLoaded(function () {
        //         //       // Drupal.siSearch.checkImage($newElements);
        //         //
        //         //       if (masonry === true) {
        //         //         Container.masonry('appended', $newElements);
        //         //       }
        //         //       Drupal.attachBehaviors(Container);
        //         //     })
        //         //       .progress(function (instance, image) {
        //         //         var result = image.isLoaded ? 'loaded' : 'broken',
        //         //           imgSrc = image.img.src, imgHeight = $(image.img).height(),
        //         //           parentH = $(image.img).parents('figure').height();
        //         //
        //         //         if ($('.exhbition-search').length && parentH > imgHeight) {
        //         //           $(image.img).addClass('landscape');
        //         //           if ($(window).width() > 499) {
        //         //             var $left = (imgHeight - parentH) / 2;
        //         //             $(image.img).css('left', $left + 'px')
        //         //           }
        //         //         }
        //         //         // if(result == 'broken') {
        //         //         //   $(image.img).addClass('hide').parents('.node--teaser').removeClass('has-media')
        //         //         // }
        //         //       });
        //         //   }
        //         // });
        //       }
        //     });
        //   });
        // }



    }
  };


})(jQuery);

