module.exports = {
  visionSidebar: {
    Guides: [
      'guides/setup',
      'guides/devices',
      'guides/lifecycle',
      'guides/formats',
      'guides/capturing',
      'guides/frame-processors',
      {
        type: 'category',
        label: 'Creating Frame Processor Plugins',
        items: [
          'guides/frame-processors-plugins-overview',
          'guides/frame-processors-plugins-ios',
          'guides/frame-processors-plugins-android',
          'guides/frame-processors-plugins-final',
        ]
      },
      'guides/frame-processor-plugin-list',
      'guides/zooming',
      'guides/focusing',
      'guides/errors',
      'guides/mocking',
      'guides/troubleshooting',
    ],
    API: [
      {
        type: 'autogenerated',
        dirName: 'api',
      }
    ],
  },
};
