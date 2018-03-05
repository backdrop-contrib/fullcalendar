/**
 * @file
 * Provides FullCalendar defaults and functions.
 */
jQuery.curCSS = function(element, prop, val) {
    return jQuery(element).css(prop, val);
};

(function ($) {

Backdrop.fullcalendar = Backdrop.fullcalendar || {};
Backdrop.fullcalendar.plugins = Backdrop.fullcalendar.plugins || {};
Backdrop.fullcalendar.cache = Backdrop.fullcalendar.cache || {};

// Alias old fullCalendar namespace.
Backdrop.fullCalendar = Backdrop.fullcalendar;

Backdrop.fullcalendar.fullcalendar = function (dom_id) {
  this.dom_id = dom_id;
  this.$calendar = $(dom_id);
  this.$options = {};
  this.navigate = false;
  this.refetch = false;

  // Hide the failover display.
  this.$calendar.find('.fullcalendar-content').hide();

  // Allow other modules to overwrite options.
  var $plugins = Backdrop.fullcalendar.plugins;
  for (var i = 0; i < Backdrop.settings.fullcalendar[dom_id].weights.length; i++) {
    var $plugin = Backdrop.settings.fullcalendar[dom_id].weights[i];
    if ($plugins.hasOwnProperty($plugin) && $.isFunction($plugins[$plugin].options)) {
      $.extend(this.$options, $plugins[$plugin].options(this, Backdrop.settings.fullcalendar[this.dom_id]));
    }
  }

  this.$calendar.find('.fullcalendar').once().fullCalendar(this.$options);

  $(this.$calendar).delegate('.fullcalendar-status-close', 'click', function () {
    $(this).parent().slideUp();
    return false;
  });
}

Backdrop.fullcalendar.fullcalendar.prototype.update = function (result) {
  var fcStatus = $(result.dom_id).find('.fullcalendar-status');
  if (fcStatus.is(':hidden')) {
    fcStatus.html(result.msg).slideDown();
  }
  else {
    fcStatus.effect('highlight');
  }
  Backdrop.attachBehaviors();
  return false;
};

/**
 * Parse Backdrop events from the DOM.
 */
Backdrop.fullcalendar.fullcalendar.prototype.parseEvents = function (callback) {
  var events = [];
  var details = this.$calendar.find('.fullcalendar-event-details');
  for (var i = 0; i < details.length; i++) {
    var event = $(details[i]);
    events.push({
      field: event.data('field'),
      index: event.data('index'),
      eid: event.data('eid'),
      entity_type: event.data('entity-type'),
      title: event.attr('title'),
      start: event.data('start'),
      end: event.data('end'),
      url: event.attr('href'),
      allDay: (event.data('all-day') === 1),
      className: event.data('cn'),
      editable: (event.data('editable') === 1),
      dom_id: this.dom_id
    });
  }
  callback(events);
};

}(jQuery));
