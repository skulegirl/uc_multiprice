(function ($) {
Drupal.behaviors.country_dropdown = {
  attach: function (context, settings) {
    var settings = settings || Drupal.settings;

    if (settings.country_dropdown) {
      var flags, msddSettings;
      for (key in settings.country_dropdown) {
        msddSettings = settings.country_dropdown[key].jsWidget;
        flags = msddSettings.countryicons;
        if (flags) {
          $.each(flags, function(index, value) {
            if (msddSettings.widget == "msdropdown") {
              $('select#country-dropdown-select-' + key + ' option[value="' + index + '"]').attr('data-image', value);
            }
            else if (msddSettings.widget == "ddslick" && Boolean(msddSettings.showSelectedHTML)) {
              $('select#country-dropdown-select-' + key + ' option[value="' + index + '"]').attr('data-imagesrc', value);
            }
          });
        }

        if (msddSettings.widget == "msdropdown") {
          try {
            $('select#country-dropdown-select-' + key).msDropDown({
              visibleRows: msddSettings.visibleRows,
              roundedCorner: Boolean(msddSettings.roundedCorner),
              animStyle: msddSettings.animStyle,
              event: msddSettings.event,
              mainCSS: msddSettings.mainCSS
            });
          }
          catch (e) {
            if (console) { console.log(e); }
          }
        }
        else if (msddSettings.widget == "chosen") {
          $('select#country-dropdown-select-' + key).chosen({
            disable_search: msddSettings.disable_search,
            no_results_text: msddSettings.no_results_text
          });
        }
        else if (msddSettings.widget == "ddslick") {
          $.data(document.body, 'ddslick'+key+'flag', 0);
          $('select#country-dropdown-select-' + key).ddslick({
            width: msddSettings.width,
            height: (msddSettings.height == 0) ? null : msddSettings.height,
            showSelectedHTML: Boolean(msddSettings.showSelectedHTML),
            imagePosition: msddSettings.imagePosition,
            onSelected: function(data) {
              var i = $.data(document.body, 'ddslick'+key+'flag');
              if (i) {
                $.data(document.body, 'ddslick'+key+'flag', 0);
                var country = data.selectedData.value;
                var href = $('#country-dropdown-select-'+key).parents('form').find('input[name="' + country + '"]').val();
                window.location.href = href;
              }
              $.data(document.body, 'ddslick'+key+'flag', 1);
            }
          });
        }
      }
    }

    $('select.country-dropdown-select-element').change(function() {
      var country = this.options[this.selectedIndex].value;

      key = encodeURI('country'); value = encodeURI(country);

      var kvp = document.location.search.substr(1).split('&');
      var i=kvp.length; var x; while(i--) 
      {
          x = kvp[i].split('=');
          if (x[0]==key)
          {
              x[1] = value;
              kvp[i] = x.join('=');
              break;
          }
      }
      if(i<0) {kvp[kvp.length] = [key,value].join('=');}

      //this will reload the page, it's likely better to store this until finished
      document.location.search = kvp.join('&'); 
    });

    $('form.country-dropdown-form').after('<div style="clear:both;"></div>');
  }
};
})(jQuery);
